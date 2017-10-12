#include "ClubInfoUpdateCommand.h"
#include "JudoMasterApplication.h"
#include "commands/ClubCommands.h"
#include "dialogs/ClubDataDialog.h"

ClubInfoUpdateCommand::ClubInfoUpdateCommand(QObject* parent, int clubId)
    : BaseCommand(parent),
      m_clubId(clubId)
{

}


ClubInfoUpdateCommand::~ClubInfoUpdateCommand()
{

}

bool ClubInfoUpdateCommand::run(IDocument *const doc)
{

    GetClubCmdPtr getClubCmd = GetClubCmdPtr(new GetClubCommand(m_clubId));

    if(JMApp()->commandController()->doCommand(getClubCmd))
    {
        Club club = getClubCmd->club();
        Q_ASSERT(club.isValid());
        m_club = club;  // Save the original data for undo.
        ClubDataDialog dlg(club, dynamic_cast<QWidget *>(parent()));

        if(dlg.exec() == QDialog::Accepted)
        {
            club = dlg.getClub();
            UpdateClubCmdPtr updateClub = UpdateClubCmdPtr (new UpdateClubCommand(club));

            return JMApp()->commandController()->doCommand(updateClub);
        }
    }

    return false;
}


