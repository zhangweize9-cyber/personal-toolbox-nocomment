FROM archlinux:latest

RUN echo 'Server = https://mirrors.tuna.tsinghua.edu.cn/archlinux/$repo/os/$arch' > /etc/pacman.d/mirrorlist && \
    pacman -Sy --noconfirm && \
    pacman -Sy --noconfirm \
    base-devel \
    cmake \
    git \
    neovim \
    nodejs \
    npm \
    && pacman -Scc --noconfirm

WORKDIR /factory

COPY . .

CMD ["/bin/bash"]
