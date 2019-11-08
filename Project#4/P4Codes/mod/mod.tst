load mod.hack,
output-file mod.out,
compare-to mod.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,
set RAM[1] 9,
set RAM[2] 0,
repeat 100 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 4,
set RAM[1] 9,
set RAM[2] 0,
repeat 100 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 9,
set RAM[1] 9,
set RAM[2] 0,
repeat 100 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 12,
set RAM[1] 9,
set RAM[2] 0,
repeat 100 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 123,
set RAM[1] 9,
set RAM[2] 0,
repeat 400 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 603,
set RAM[1] 37,
set RAM[2] 0,
repeat 400 {
	ticktock;
}
output;

set PC 0,
set RAM[0] 63,
set RAM[1] 137,
set RAM[2] 0,
repeat 200 {
	ticktock;
}
output;

