/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#ifndef OPENDDS_IDL_BE_INTERFACE_H
#define OPENDDS_IDL_BE_INTERFACE_H

#include <ace/SString.h>

#include "language_mapping.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class BE_Interface {
public:
  virtual ~BE_Interface() {}

  // Provide a language mapping
  LanguageMapping* language_mapping() {
    return 0;
  }

  // Extern BE_* functions
  virtual int init(int&, ACE_TCHAR*[]) = 0;
  virtual void post_init(char*[], long) = 0;
  virtual void version() const = 0;
  virtual void produce() = 0;
  virtual void cleanup() = 0;

  // Externally called BE_GlobalData methods
  virtual void destroy() = 0;
  virtual void parse_args(long& i, char** av) = 0;

  // Called by be_util
  virtual void prep_be_arg(char* arg) = 0;
  virtual void arg_post_proc() = 0;
  virtual void usage() = 0;
};

#endif /* OPENDDS_IDL_BE_INTERFACE_H */
