FROM centos:7.6.1810

# Setup some of out environment variables for the toolchain
ENV IDF_PATH=/esp-idf \
    PATH=$PATH:/xtensa-esp32-elf/bin:/esp-idf/tools

# Pull in the archive of the toolchain. Adding it from context, instead of using a URL, to more easily version the toolchain.
ADD esp32-elf-linux64-toolchain.tar.gz /

# Install some pre-req packages, including some things from EPEL like cmake 3+ and pip
RUN yum install -y epel-release && \
    yum update -y && \
    yum install -y \
        git \
        vim \
        make \
        cmake3 \
        gcc \
        gcc-c++ \
        gdb \
        gdb-gdbserver \
        openocd \
        wget \
        ncurses-devel \
        flex \
        bison \
        gperf \
        ninja-build \
        ccache \
        screen \
        unzip \
        java-1.8.0-openjdk \
        java-1.8.0-openjdk-devel \
        python \
        python-pip && \
    yum clean all

# Need newer version of cmake to be used in the place of the older version of cmake.
RUN ln -sv /usr/bin/cmake3 /usr/bin/cmake

# Cloning IDF and installing required packages for the IDF
RUN git clone --recursive --depth 1 --branch v3.3-beta3 https://github.com/espressif/esp-idf.git /esp-idf && \
    pip install --upgrade pip && \
    pip install -r /esp-idf/requirements.txt

CMD /bin/bash
