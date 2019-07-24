# Example 4

Example 4 adds support for an nginx reverse proxy to our application using
docker compose.

## Running the Example

Run the environment

```sh
docker-compose up
```

And access the server on [localhost:80](http://localhost:80)

## Problems

There are still several points of improvement for our container.

    - we have a seperate dockerfile that does very little for nginx
    - our contianers are running on the default network
