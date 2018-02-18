#include "buttondialog.h"

ButtonDialog::ButtonDialog(QString p_displayText, QStringList p_buttonTexts)
{
    m_vLayout = new QVBoxLayout;
    m_hLayout = new QHBoxLayout;
    m_displayText=new QLabel(p_displayText,this);

    for(int i=0;i<p_buttonTexts.length();i++)
    {
        QPushButton* pushButton=new QPushButton(p_buttonTexts[i],this);
        m_hLayout->addWidget(pushButton);
        m_buttonRow.append(pushButton);
        connect(pushButton, SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    }
    m_vLayout->addWidget(m_displayText);
    m_vLayout->addLayout(m_hLayout);
    setLayout(m_vLayout);
}

int ButtonDialog::GetClickedButtonNumber() const
{
    return m_clickedButtonNumber;
}

ButtonDialog::~ButtonDialog()
{
    for(int i=0;i<m_buttonRow.length();i++)
        delete m_buttonRow[i];
    delete m_displayText;
    delete m_hLayout;
    delete m_vLayout;
}

void ButtonDialog::ButtonClicked()
{
    // the code for getting the sender is from the internet
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    if (pButton)
    {
        for(int i=0;i<m_buttonRow.length();i++)
        {
            if(pButton==m_buttonRow[i])
                m_clickedButtonNumber=i;
        }
    }
    accept();
}
