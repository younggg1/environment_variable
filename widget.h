#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>  // QLineEdit 头文件
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_java_clicked();
    void on_maven_clicked();

    void on_msql_clicked();

private:
    Ui::Widget *ui;
    // 检查路径是否包含空格的函数声明
    bool pathContainsSpaces(const QString &path);
};
#endif // WIDGET_H
