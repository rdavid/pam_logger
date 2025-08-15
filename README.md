# PAM Logger [![Hits-of-Code](https://hitsofcode.com/github/rdavid/pam_logger?branch=master)](https://hitsofcode.com/view/github/rdavid/pam_logger?branch=master) [![License](https://img.shields.io/badge/license-0BSD-green)](https://github.com/rdavid/pam_logger/blob/master/LICENSE)
PAM module to collect user data

* [About](#about)
* [Install](#install)
* [License](#license)

## About
This project implements a Pluggable Authentication Module (PAM) that implements
the `pam_sm_authenticate` API to capture user authentication details such as
username, service, and remote host during login events.
The collected data is appended to `/tmp/pam_logger.log` in a structured format
for auditing, compliance checks, and security monitoring.
This module is lightweight, tested on Debian, and can be integrated into
authentication workflows without modifying existing services.

## Install
Disable authentication timeout for sudo:
```
https://askubuntu.com/questions/636092/how-to-get-sudo-to-prompt-you-for-a-password-each-time
```
Configure pam sudo:
```
sudo sed -i '2s/^/auth sufficient pam_logger.so/' /etc/pam.d/sudo
```
Compile and install the module:
```
make install
```
From this point all sudo commands will be logged at `/tmp/pam_logger.log`.

## License
PAM Logger is copyright [David Rabkin](http://cv.rabkin.co.il) and
available under a [Zero-Clause BSD license](https://github.com/rdavid/pam_logger/blob/master/LICENSE).
