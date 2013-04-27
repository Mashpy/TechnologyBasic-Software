#include <QtGui/QApplication>
#include "mainwindow.h"
#include "fvupdater.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Prerequisite for the Fervor updater
//        QApplication::applicationName("TechnologyBasic");
        QApplication::setOrganizationName("TechnologyBasic");
	QApplication::setOrganizationDomain("pypt.lt");

	// Set feed URL before doing anything else
        FvUpdater::sharedUpdater()->SetFeedURL("http://technologybasic.com/desktop-apps/Appcast.xml");

	// Check for updates automatically
	FvUpdater::sharedUpdater()->CheckForUpdatesSilent();


	// Show main window
	MainWindow w;
     //   w.setWindowState(w.windowState()|);
	w.show();
	
	return a.exec();
}
