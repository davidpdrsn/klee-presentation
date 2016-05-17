FROM klee/klee

RUN mkdir /home/klee/app
WORKDIR /home/klee/app
COPY . /home/klee/app/
