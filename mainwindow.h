#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class TokenList;
class SyntaxTree;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void printLexer();
    void printParser();
private:
    Ui::MainWindow* ui;
    TokenList* tokenList;
    SyntaxTree* syntaxTree;
};
#endif // MAINWINDOW_H
