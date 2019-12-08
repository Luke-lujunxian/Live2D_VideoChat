#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

namespace Ui {
class SettingWin;
}

class SettingWin : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWin(QWidget *parent = nullptr);
    ~SettingWin();

public slots:
    void canApply();
private slots:
    void on_pushButton_Apply_clicked();
    void on_pushButton_ProfilePhoto_clicked();
    void on_pushButton_Model_clicked();
private:
    Ui::SettingWin *ui;
};

#endif // SETTING_H
