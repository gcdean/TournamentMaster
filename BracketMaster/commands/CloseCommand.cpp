#include "CloseCommand.h"

#include "JudoMasterApplication.h"
#include "commands/SaveCommand.h"

#include <QMessageBox>

CloseCommand::CloseCommand()
{

}

CloseCommand::~CloseCommand()
{

}

bool CloseCommand::run()
{
    if(JMApp()->isModified())
    {
        // Ask if the user wants to save.
        if(QMessageBox::Yes == QMessageBox::question(dynamic_cast<QWidget *>(parent()), "Modified", "File has been modified. Do you want to save?"))
        {
            // Call Save Command
            SaveCommand saveCmd(false, this);
            if(!saveCmd.run())
            {
                return done(false);
            }
        }
    }

    JMApp()->setTournament(nullptr);
    JMApp()->setModified(false);

    return done(true);
}
