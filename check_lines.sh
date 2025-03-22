clear
/usr/bin/g++ -o ./tools/count_lines ./tools/count_lines.cpp

/usr/bin/echo "============================O============================"
/usr/bin/echo "Counting Clients lines [DIR: ./clients]:"
client_lines=$(./tools/count_lines ./client/include/LoadImage.hpp ./client/include/Person.hpp ./client/include/Game.hpp ./client/include/TimeBox.hpp ./client/include/Block.hpp ./client/main.cpp)
echo "$client_lines"

/usr/bin/echo "============================O============================"
/usr/bin/echo "Counting Server  lines [DIR: ./server ]:"
server_lines=$(./tools/count_lines ./server/include/server.hpp ./server/include/client.hpp)
echo "$server_lines"

/usr/bin/echo "============================O============================"
/usr/bin/echo "Counting Tools   lines [DIR: ./tools  ]:"
tools_lines=$(./tools/count_lines ./tools/count_lines.cpp ./tools/calcScore.cpp ./tools/list_files.cpp)
echo "$tools_lines"