#include "JudoMasterApplication.h"

#include "CommandController.h"
#include "TournamentDoc.h"

JudoMasterApplication *JMApp()
{
    return dynamic_cast<JudoMasterApplication *>(qApp);
}


JudoMasterApplication::JudoMasterApplication(int &argc, char **argv) :
    QApplication(argc, argv)
    , m_lastSaveDir(QDir::home())
{

    QCoreApplication::setOrganizationName("Emerald City Judo");
    QCoreApplication::setOrganizationName("emeraldcityjudo.com");
    QCoreApplication::setApplicationName("TournamentMaster");


    QSettings settings;
    m_lastSaveDir = settings.value("lastSaveDir").toString();

    QSharedPointer<TournamentDoc> doc = QSharedPointer<TournamentDoc>(new TournamentDoc);
    QSharedPointer<CommandController> teditor = QSharedPointer<CommandController>(new CommandController(doc));

    setCommandController(teditor);

    connect(this, &QCoreApplication::aboutToQuit, this, &JudoMasterApplication::saveState);


}

void JudoMasterApplication::setCommandController(QSharedPointer<CommandController> editor)
{
    m_commandController = editor;

    emit tournamentChanged();

}

CommandController* JudoMasterApplication::commandController()
{

    return m_commandController.data();
}

bool JudoMasterApplication::isModified() const
{
    return m_modified;
}

void JudoMasterApplication::setModified(bool modified)
{
    m_modified = modified;
}

const QDir JudoMasterApplication::lastSaveDir() const
{
    return m_lastSaveDir;
}

void JudoMasterApplication::setLastSaveDir(QDir dirname)
{
    m_lastSaveDir = dirname;
}

void JudoMasterApplication::saveState()
{
    QSettings settings;
    settings.setValue("lastSaveDir", m_lastSaveDir.absolutePath());
}
