# Example 5

Example 5 removes our custom nginx docker image and instead uses volumes
to route our local file to the server. Moreover, we use an internal
network to access our containers.

## Running the Example

Run the environment

```sh
docker-compose up
```

And access the server on [localhost:80](http://localhost:80)
