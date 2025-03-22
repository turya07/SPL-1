cur_path=$pwd
/usr/bin/g++ -o ./client/game.out ./client/main.cpp -lsfml-graphics -lsfml-window -lsfml-system
/usr/bin/make ./server/server
/usr/bin/make ./server/client

cd ./client
./game.out
cd $cur_path