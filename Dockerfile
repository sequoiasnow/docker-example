FROM alpine

EXPOSE 3000

# Install the tools we need to build our C program
RUN apk add -U gcc libc-dev

# Set the current working director
WORKDIR /var/www

# Copy our code
COPY server.c .

# Build our program and ensure its executable
RUN gcc server.c -o server && chmod +x server

CMD ["/var/www/server"]
