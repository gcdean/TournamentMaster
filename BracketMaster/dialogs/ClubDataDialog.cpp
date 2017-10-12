#include "ClubDataDialog.h"
#include "ui_ClubDataDialog.h"

#include <QPushButton>


namespace
{
    QString states = "AL,AK,AZ,AR,CA,CO,CT,DE,FL,GA,HI,ID,IL,IN,IA,KS,KY,LA,ME,MD,MA,MI,MN,MS,MO,MT,NE,NV,NH,NJ,NM,NY,NC,ND,OH,OK,OR,PA,RI,SC,SD,TN,TX,UT,VT,VA,WA,WV,WI,WY";

    QString provinces = "AB,BC,MB,NB,NL,NS,NT,NU,ON,PE,QC,SK,YT";
}

ClubDataDialog::ClubDataDialog(Club club, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClubDataDialog),
    m_club(club)
{
    ui->setupUi(this);

    connect(ui->usaBtn, &QPushButton::toggled, this, &ClubDataDialog::updateStateList);
    connect(ui->canadaBtn, &QPushButton::toggled, this, &ClubDataDialog::updateStateList);
    connect(ui->otherCountryBtn, &QPushButton::toggled, this, &ClubDataDialog::updateStateList);

    updateControls();
}


ClubDataDialog::~ClubDataDialog()
{
    delete ui;
}

Club ClubDataDialog::getClub()
{
    updateClub();
    return m_club;
}

void ClubDataDialog::updateControls()
{
    ui->clubNameEdit->setText(m_club.clubName());
    ui->coachNameEdit->setText(m_club.coachName());
    ui->address1Edit->setText(m_club.address1());
    ui->address2Edit->setText(m_club.address2());
    ui->cityEdit->setText(m_club.city());
    ui->zipEdit->setText(m_club.zip());

    ui->stateCombo->clear();
    if(m_club.country().isEmpty() || m_club.country().compare("usa", Qt::CaseInsensitive) == 0)
    {
        ui->usaBtn->setChecked(true);
    }
    else if(m_club.country().compare("canada", Qt::CaseInsensitive) == 0)
    {
        ui->canadaBtn->setChecked(true);
    }
    else
    {
        ui->otherCountryBtn->setChecked(true);
    }
    updateStateList();


}

void ClubDataDialog::updateStateList()
{
    ui->stateCombo->clear();
    ui->otherCountryEdit->setText("");
    if(ui->usaBtn->isChecked())
    {
        // US States
        ui->stateCombo->addItems(states.split(","));
    }
    else if(ui->canadaBtn->isChecked())
    {
        // Canadian Provinces
        ui->stateCombo->addItems(provinces.split(","));
    }
    else
    {
        ui->otherCountryEdit->setText(m_club.country());

    }
    ui->stateCombo->setCurrentText(m_club.state().toUpper());

}

void ClubDataDialog::updateClub()
{
    m_club.setClubName(ui->clubNameEdit->text());
    m_club.setCoachName(ui->coachNameEdit->text());
    m_club.setAddress1(ui->address1Edit->text());
    m_club.setAddress2(ui->address2Edit->text());
    m_club.setCity(ui->cityEdit->text());
    m_club.setState(ui->stateCombo->currentText());
    QString country;
    if(ui->usaBtn->isChecked())
    {
        country = "USA";
    }
    else if(ui->canadaBtn->isChecked())
    {
        country = "Canada";
    }
    else
    {
        country = ui->otherCountryEdit->text();
    }
    m_club.setCountry(country);
    m_club.setZip(ui->zipEdit->text());

}
