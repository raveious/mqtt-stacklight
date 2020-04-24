FROM centos:7.6.1810

# Setup some of out environment variables for the toolchain
ENV IDF_PATH=/esp-idf \
    PATH=$PATH:/xtensa-lx106-elf/bin:/esp-idf/tools

# Pull in the archive of the toolchain. Adding it from context, instead of using a URL, to more easily version the toolchain.
ADD xtensa-lx106-elf-linux64-1.22.0-100-ge567ec7-5.2.0.tar.gz /

# Install some pre-req packages, including some things from EPEL like cmake 3+ and pip
# Also need newer version of cmake to be used in the place of the older version of cmake.
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
        ncurses-devel \
        flex \
        bison \
        gperf \
        unzip \
        python \
        python-pip && \
    yum clean all && \
    ln -sv /usr/bin/cmake3 /usr/bin/cmake

# Cloning IDF and installing required packages for the IDF
RUN git clone --recursive --depth 1 --branch v3.3-rc1 https://github.com/espressif/ESP8266_RTOS_SDK.git /esp-idf && \
    find /esp-idf/tools -type d -exec chmod a+w {} + && \
    pip install --upgrade pip && \
    pip install -r /esp-idf/requirements.txt

CMD /bin/bash
