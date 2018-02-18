#include "startdialog.h"

#include <QFileDialog>

StartDialog::StartDialog()
{
    m_vLayout = new QVBoxLayout;
    m_okButton= new QPushButton("OK",this);
    m_loadFileButton = new QPushButton("Load game", this);
    m_playerOptions=new QComboBox(this);
    m_displayText=new QLabel("With how many players do you want to play?",this);

    AddPlayerOptions();

    m_vLayout->addWidget(m_displayText);
    m_vLayout->addWidget(m_playerOptions);
    m_vLayout->addWidget(m_okButton);
    m_vLayout->addWidget(m_loadFileButton);
    setLayout(m_vLayout);    

    //disable the close button (X)
    setWindowFlags(Qt::WindowTitleHint);

    connect(m_okButton,SIGNAL(clicked()),this, SLOT(accept()));
    connect(m_loadFileButton, SIGNAL(clicked()), this, SLOT(LoadFileButtonClicked()));
}

StartDialog::~StartDialog()
{
    delete m_okButton;
    delete m_playerOptions;
    delete m_vLayout;
}

int StartDialog::GetSelectedValue()
{
    return m_playerOptions->currentIndex()+2;
}

bool StartDialog::LoadFileSelected()
{
    return !m_loadFileName.isEmpty();
}

QString StartDialog::GetLoadFile()
{
    return m_loadFileName;
}

void StartDialog::LoadFileButtonClicked()
{

    m_loadFileName = QFileDialog::getOpenFileName(this, "Load game");

    accept();
}

void StartDialog::AddPlayerOptions()
{
    QStringList list;
    list << "2" << "3" << "4" << "5" << "6" << "7" << "8";

    m_playerOptions->addItems(list);
}
