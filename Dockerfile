FROM debian:wheezy
MAINTAINER Vincent Ambo <tazjin@gmail.com>

# Install build-dependencies
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get install -y git cmake build-essential\
    libbz2-dev libssl-dev libace-dev libmysql++-dev liblua5.2-dev lua5.2

# Copy source
ADD . /opt/mangos/src

# Build & install
RUN mkdir /opt/mangos/build && cd /opt/mangos/build \
    && cmake -DCMAKE_INSTALL_PREFIX=/opt/mangos -DCMAKE_BUILD_TYPE=Release ../src \
    && make && make install

# Add launch script
ADD docker-launch.sh /usr/bin/mangos-launch
RUN chmod 755 /usr/bin/mangos-launch

VOLUME ["/opt/mangos/etc", "/opt/mangos/wow", "/opt/mangos/data"]
EXPOSE 8085 3724

CMD /usr/bin/mangos-launch
