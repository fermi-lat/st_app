/** \file st_app_main.cxx
    \brief Standard main for ballistic Science Tools applications. Applications should #include this
    file, but precede the inclusion by a static definition of an object of a subclass of IApp.
    \author James Peachey, HEASARC
*/

#include <iostream>
#include <stdexcept>
#include <typeinfo>

#include "st_app/StApp.h"
#include "st_app/StAppFactory.h"

int main(int argc, char ** argv) {
  int status = 0;
  st_app::StApp * app = 0;

  try {
    try {
      // Process command line arguments. This will throw if the real application code
      // cannot/should not start.
      st_app::StApp::processCommandLine(argc, argv);

      // Create an application using the singleton factory. Client code must have instantiated a single
      // instance of a subclass of IAppFactory.
      app = st_app::IStAppFactory::instance().createApp();

      // Run the application.
      app->run();

    } catch (const std::exception & x) {
      // Return a non-zero exit code:
      status = 1;

      // Report the type of the exception if possible, using typeid; typeid can throw so be careful:
      const char * info = typeid(x).name();
      std::cerr << "Caught " << info << " at the top level: " << x.what() << std::endl;
    }
  } catch (...) {
    // Return a non-zero exit code:
    status = 2;

    // Report the error more generically:
    std::cerr << "Caught unknown object at the top level." << std::endl;
  }

  delete app;

  return status;
}
