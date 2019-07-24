FROM alpine as builder

# Install the tools we need to build our C program
RUN apk add -U gcc libc-dev

# Set the current working director
WORKDIR /var/www

# Copy our code
COPY server.c .

# Build our program and ensure its executable
RUN gcc -static server.c -o server
RUN chmod +x server


FROM scratch

EXPOSE 3000

WORKDIR /var/www

COPY --from=builder /var/www/server /var/www/server

CMD ["/var/www/server"]
