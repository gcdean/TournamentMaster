#include "CloseCommand.h"

#include "JudoMasterApplication.h"
#include "commands/CreateTournamentCommand.h"
#include "commands/SaveCommand.h"

#include <QMessageBox>

CloseCommand::CloseCommand()
{

}

CloseCommand::~CloseCommand()
{

}

bool CloseCommand::run(IDocument *const doc)
{
    if(doc->isModified())
    {
        // Ask if the user wants to save.
        if(QMessageBox::Yes == QMessageBox::question(dynamic_cast<QWidget *>(parent()), "Modified", "File has been modified. Do you want to save?"))
        {
            // Call Save Command
            SaveCommand saveCmd(false, this);
            if(!saveCmd.run(doc))
            {
                return done(false);
            }
        }
    }

    // TODO - more to do here.
    // Now, create a new, empty tourament.
    CreateTournamentCmdPtr createCmd = CreateTournamentCmdPtr(new CreateTournamentCommand);
    createCmd->run(doc);

    return done(true);
}
