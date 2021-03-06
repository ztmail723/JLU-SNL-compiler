#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "lexerimp.h"
#include "parserll1.h"
#include "parserrecursivedescent.h"
#include <QDebug>

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
    if (fileNames.size() == 0)
    {
        return;
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
    this->printLexer(); // 显示词法分析的结果
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
    this->printParser(); // 显示语法分析的结果
}

void MainWindow::printLexer() // 显示词法分析的结果
{
    ui->listWidget->clear();
    int tokenSize = this->tokenList->size();
    for (int i = 0; i < tokenSize; i++)
    {
        QString lineStr = "Line " + QString::number((*this->tokenList)[i].getLineShow());
        QString lexStr = ConstantVar::lexName[(*this->tokenList)[i].getLexType()];
        QString semStr = (*this->tokenList)[i].getSem();
        ui->listWidget->addItem(lineStr + " " + lexStr + " " + semStr);
    }
}

void MainWindow::printParser() // 显示语法分析的结果
{
    ui->treeWidget->clear();
    TreeNode* root = this->syntaxTree->getRoot();
    QTreeWidgetItem* topItem = new QTreeWidgetItem(ui->treeWidget);
    QString str = ConstantVar::nodekindName[root->nodekind];
    topItem->setText(0, str);
    for (int i = 0; i < 3; i++)
    {
        if (root->child[i] == nullptr)
        {
            continue;
        }
        this->preOrder(root->child[i], topItem);
    }
}

void MainWindow::preOrder(TreeNode* node, QTreeWidgetItem* parentItem)
{
    QTreeWidgetItem* nowItem = new QTreeWidgetItem(parentItem);
    if (node->sibling != nullptr)
    {
        this->preOrder(node->sibling, parentItem);
    }
    QString str = ConstantVar::nodekindName[node->nodekind];

    // 以下用于显示标识符
    for (int i = 0; i < 10; i++)
    {
        if (node->name[i] != "")
        {
            if (i != 0)
            {
                str += ",";
            }
            else
            {
                str += ":";
            }
            str += node->name[i];
        }
    }

    nowItem->setText(0, str);
    for (int i = 0; i < 3; i++)
    {
        if (node->child[i] == nullptr)
        {
            continue;
        }
        this->preOrder(node->child[i], nowItem);
    }
}
