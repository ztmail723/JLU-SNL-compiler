#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "lexerimp.h"
#include "parserll1.h"
#include "parserrecursivedescent.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    tokenList = nullptr;
    syntaxTree = nullptr;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete tokenList;
    delete syntaxTree;
    delete ui;
}


void MainWindow::on_pushButton_clicked() // 从文件中读取
{
    //定义文件对话框类
    QFileDialog* fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(QStringLiteral("选中文件"));
    //设置默认文件路径
    // fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("文本文件(*.txt)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    QFile file(fileNames.back());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    ui->textEdit->setText(QString(t));
    file.close();
}

void MainWindow::on_pushButton_2_clicked() // 进行词法分析
{
    Lexer* lexer = new LexerImp();
    if (this->tokenList != nullptr)
    {
        delete this->tokenList;
        this->tokenList = nullptr;
    }
    this->tokenList = lexer->run(ui->textEdit->toPlainText());
    delete lexer;
}

void MainWindow::on_pushButton_3_clicked() // 进行语法分析
{
    if (this->tokenList == nullptr)
    {
        QMessageBox::about(nullptr, "提示", "尚未进行词法分析，无法进行语法分析");
        return;
    }
    int selectedID = ui->comboBox->currentIndex();
    Parser* parser = nullptr;
    if (selectedID == 0)
    {
        parser = new ParserRecursiveDescent(); // 递归下降
    }
    else
    {
        parser = new ParserLL1(); // LL1
    }
    if (this->syntaxTree != nullptr)
    {
        delete this->syntaxTree;
        this->syntaxTree = nullptr;
    }
    this->syntaxTree = parser->run(*this->tokenList);
}
