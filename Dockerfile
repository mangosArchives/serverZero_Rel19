FROM debian:wheezy
MAINTAINER Vincent Ambo <tazjin@gmail.com>

# This Dockerfile sets up a MaNGOSZero container running both mangos and realmd
# under supervisor.
# It expects the extracted maps and DBCs to be mounted into /opt/mangos/data and
# configuration files into /opt/mangos/etc on the container.

# Basics
ENV DEBIAN_FRONTEND noninteractive
VOLUME ["/opt/mangos/etc", "/opt/mangos/data", "/opt/mangos/logs"]
EXPOSE 8085 3724
CMD ["/usr/bin/supervisord"]

# Install build-dependencies & supervisord
RUN apt-get update && apt-get install -y git cmake build-essential libssl-dev\
    libbz2-dev supervisor libace-dev libmysql++-dev liblua5.2-dev lua5.2

# Add supervisor config & launch script
ADD docker-supervisord.conf /etc/supervisor/conf.d/mangos.conf

# Copy source
ADD . /opt/mangos/src

# Build & install
RUN mkdir /opt/mangos/build && cd /opt/mangos/build \
    && cmake -DCMAKE_INSTALL_PREFIX=/opt/mangos -DCMAKE_BUILD_TYPE=Release ../src \
    && make && make install
