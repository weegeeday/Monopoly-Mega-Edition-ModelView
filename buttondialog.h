// Made by Louis Hendrikx

#ifndef BUTTONDIALOG_H
#define BUTTONDIALOG_H
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QList>
#include <QPushButton>

class ButtonDialog:public QDialog
{
    Q_OBJECT
public:
    ButtonDialog(QString p_displayText, QStringList p_buttonTexts);
    int GetClickedButtonNumber() const;
    ~ButtonDialog();
public slots:
    void ButtonClicked();

private:
    QPushButton* m_okButton;
    QVBoxLayout* m_vLayout;
    QHBoxLayout* m_hLayout;
    QList <QPushButton*> m_buttonRow;
    QLabel * m_displayText;
    int m_clickedButtonNumber;
};

#endif // BUTTONDIALOG_H
