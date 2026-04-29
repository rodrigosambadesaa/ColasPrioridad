FROM gcc:14

WORKDIR /app
COPY . .

RUN make

CMD ["./app"]
