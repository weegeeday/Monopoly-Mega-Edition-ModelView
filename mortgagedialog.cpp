#include "mortgagedialog.h"

MortgageDialog::MortgageDialog(Player* p_player, QWidget* parent) : QDialog(parent)
{

    m_currentPlayer = p_player;

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okButton = new QPushButton("Ok");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), this, SLOT(OkButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    CreateCheckBoxes(mainLayout);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

}

QMap<Property *, bool> MortgageDialog::GetMortgagedProperties() const
{
    return m_mortgageProperties;
}

void MortgageDialog::OkButtonClicked()
{
    QList<Property*> properties = m_currentPlayer->GetProperties();


    for (int i = 0; i < m_checkboxes.length(); i++)
    {
        m_mortgageProperties[properties[i]] = m_checkboxes[i]->isChecked();
    }

    accept();
}

void MortgageDialog::CreateCheckBoxes(QVBoxLayout *p_mainLayout)
{
    QList<Property*> properties = m_currentPlayer->GetProperties();

    for (int i = 0; i < properties.length(); i++)
    {
        QCheckBox* checkBox = new QCheckBox(properties[i]->GetName() + " (Mortgage: " + QString::number(properties[i]->GetMortgagePrice()) + ")");
        checkBox->setChecked(properties[i]->GetInMortgage());
        m_checkboxes.append(checkBox);
        p_mainLayout->addWidget(checkBox);
    }

}
