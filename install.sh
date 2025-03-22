cur_path=$pwd
/usr/bin/g++ -o ./client/game.out ./client/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
/usr/bin/make ./server/server
/usr/bin/make ./server/client

echo "Successfully compiled the game!"
cd ./client
./game.out
#echo "Type \`cd ./client\`"
#echo "Then type \`./game.out\` to run the game"

cd $cur_path
