FROM ubuntu:22.04
RUN apt-get update && apt-get install -y build-essential g++ python3 python3-pip && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . /app
RUN make
RUN pip3 install flask
CMD ["/app/scheduler"]
