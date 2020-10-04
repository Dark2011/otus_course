FROM ubuntu:18.04

RUN apt update && apt install -y --no-install-recommends \
	sudo \
	iputils-ping \
	git \
	build-essential \
        libboost-all-dev \
	openssh-client \
        ca-certificates \
	pkg-config && \
	echo "deb [trusted=yes] http://dl.bintray.com/dark2011/otus_hw trusty main" | sudo tee -a /etc/apt/sources.list && \
	apt update && apt install -f -y helloworld

ENTRYPOINT ["helloworld"] 
