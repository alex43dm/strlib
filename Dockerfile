FROM archlinux
LABEL Description="strlib build" Vendor="Alex" Version="1.0"
RUN pacman --noconfirm -Syu &&  pacman --noconfirm -S gcc git make gtest && git clone https://github.com/alex43dm/strlib.git && cd strlib && make test
