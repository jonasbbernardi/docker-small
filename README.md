
# Docker Small Images

Files to generate the lesser possible docker image.

"Hello World" size: 42.82 Kb
"Small Server" size: 60.54

## Setup

There is three Dockerfile in this repos:

- **Dockerfile-compiler**: It can be used to compile a .c file, if you want to get compiled file for any reason.
- **Dockerfile-hello**: Simple "hello world" printer on command line.
- **Dockerfile-server**: Start a http server to response `GET /` requests with a simple `{"success": true}`.

Dockerfile-compiler is compiling `hello.c` file, to compile `server.c` file, change it.

Files compiled can be used to build images faster, if is your intention, use `Dockerfile-compiler` to create executable files, then create a `Dockerfile` like this:

```dockerfile
FROM scratch
ADD hello /
CMD ["/hello"]
```

To build and run images, use commands as bellow.

**Commands:**

```bash
# Hello
docker build -t small-image -f Dockerfile-hello .
docker run --rm --name small-image small-image
# Server
docker build -t small-image -f Dockerfile-server .
docker run --rm -p 8080:8080 --name small-image small-image
# Copy files
docker build -t extract-file -f Dockerfile-compiler
docker create --name extract-file extract-file
docker cp extract-file:/server ./server
docker rm extract-file
```

\* _The rm parameter is used to remove the container after its execution._

## AWS ECR

To send image to AWS ECR, install aws cli, login to ECR and use build/push commands, as per the following example.

```bash
# Log in docker to ECR
aws ecr get-login-password --region region | docker login --username AWS --password-stdin aws_account_id.dkr.ecr.region.amazonaws.com
# Build image with tag latest pointing to ECR
docker build -t aws_account_id.dkr.ecr.region.amazonaws.com/my-repository:latest -f Dockerfile-xxx .
# Publish image with latest tag
docker push aws_account_id.dkr.ecr.region.amazonaws.com/my-repository:latest
```

## Azure ACR

To send image to Azure ACR, install azure cli, login to ACR and use build/push commands, as per the following example.

```bash
# Log in docker to ACR
az acr login --name acr-name
# Build image with tag latest pointing to ACR
docker build -t acr-name.azurecr.io/image-name:latest -f Dockerfile-xxx .
# Publish image with latest tag
docker push acr-name.azurecr.io/image-name:latest
```

## References

- [Docker Scratch Image][docker-scratch]
- [Docker Alpine Image][docker-alpine]
- [C Hello World][c-hello-world]
- [GCC Install][gcc-install]
- [AWS CLI][aws-cli]
- [Azure CLI][az-cli]

<!-- References -->

[aws-cli]: https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-getting-started.html
[az-cli]: https://learn.microsoft.com/en-us/cli/azure/get-started-with-azure-cli
[c-hello-world]: https://stackoverflow.com/questions/12355758/proper-hello-world-in-c
[docker-alpine]: https://hub.docker.com/_/alpine
[docker-scratch]: https://hub.docker.com/_/scratch
[gcc-install]: https://gcc.gnu.org/install/
