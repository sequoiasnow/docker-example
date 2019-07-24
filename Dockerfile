FROM alpine

EXPOSE 3000

# Install the tools we need to build our C program
RUN apk add -U gcc libc-dev

# Set the current working director
WORKDIR /var/www

# Copy our code
COPY . .

# Build our program
RUN gcc server.c -o server

# Make sure our program executable
RUN chmod +x server

CMD ["/var/www/server"]
