#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <stdio.h>

PAM_EXTERN int pam_sm_authenticate(
  pam_handle_t *handle,
  int flags,
  int argc,
  const char **argv) {
  (void)handle;
  (void)flags;
  (void)argc;
  (void)argv;
  //const char fname[] = "/tmp/pam_logger.log";
  printf("Welcome, foobar\n");
  return PAM_SUCCESS;
}
