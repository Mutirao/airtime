/*------------------------------------------------------------------------------

    Copyright (c) 2004 Media Development Loan Fund
 
    This file is part of the LiveSupport project.
    http://livesupport.campware.org/
    To report bugs, send an e-mail to bugs@campware.org
 
    LiveSupport is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
  
    LiveSupport is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with LiveSupport; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 
    Author   : $Author: maroy $
    Version  : $Revision: 1.3 $
    Location : $Source: /home/paul/cvs2svn-livesupport/newcvsrepo/livesupport/products/gLiveSupport/src/main.cxx,v $

------------------------------------------------------------------------------*/

/** @file
 *  This file contains the main entry point to the Scheduler daemon.
 */

/* ============================================================ include files */

#ifdef HAVE_CONFIG_H
#include "configure.h"
#endif

#include <iostream>

#include <unicode/resbund.h>
#include <gtkmm/main.h>

#include "LiveSupport/Core/Ptr.h"
#include "LiveSupport/Core/LocalizedObject.h"

#include "UiTestMainWindow.h"

using namespace LiveSupport::Core;
using namespace LiveSupport::GLiveSupport;

/* ===================================================  local data structures */


/* ================================================  local constants & macros */


/* ===============================================  local function prototypes */

/* =============================================================  module code */

/**
 *  Program entry point.
 *
 *  @param argc the number of command line arguments passed by the user.
 *  @param argv the command line arguments passed by the user.
 *  @return 0 on success, non-0 on failure.
 */
int main (  int     argc,
            char  * argv[] )
{
    Gtk::Main kit(argc, argv);

    UErrorCode                status = U_ZERO_ERROR;
    Ptr<ResourceBundle>::Ref  bundle(new ResourceBundle("./tmp/" PACKAGE_NAME,
                                                        "en",
                                                        status));
    if (!U_SUCCESS(status)) {
        std::cerr << "opening resource bundle a failure" << std::endl;
        exit(EXIT_FAILURE);
    }

    Ptr<UiTestMainWindow>::Ref  mainWindow(new UiTestMainWindow(bundle));

    Ptr<ResourceBundle>::Ref    loginBundle;
    try {
        loginBundle = mainWindow->getBundle("loginWindow");
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Shows the window and returns when it is closed.
    Gtk::Main::run(*mainWindow);

    exit(EXIT_SUCCESS);
}

