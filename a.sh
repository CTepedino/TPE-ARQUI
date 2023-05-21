docker start TPE
docker exec -it TPE make clean -C/root/Toolchain
docker exec -it TPE make clean -C/root/
docker exec -it TPE make all -C/root/Toolchain
docker exec -it TPE make all -C/root/
docker stop TPE
./run.sh
