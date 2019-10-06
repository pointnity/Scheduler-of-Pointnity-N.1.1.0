<?php

$q = strtolower($_GET["term"]);
if (!$q) return;
$items = array(
"Great Bittern"=>"Botaurus stellaris",
"Little Grebe"=>"Tachybaptus ruficollis",
"Black-necked Grebe"=>"Podiceps nigricollis",
"Little Bittern"=>"Ixobrychus minutus",
"Black-crowned Night Heron"=>"Nycticorax nycticorax",
"Purple Heron"=>"Ardea purpurea",
"White Stork"=>"Ciconia ciconia",
"Spoonbill"=>"Platalea leucorodia",
"Red-crested Pochard"=>"Netta rufina",
"Common Eider"=>"Somateria mollissima",
"Red Kite"=>"Milvus milvus",
"Hen Harrier"=>"Circus cyaneus",
"Montagu`s Harrier"=>"Circus pygargus",
"Black Grouse"=>"Tetrao tetrix",
"Grey Partridge"=>"Perdix perdix",
"Spotted Crake"=>"Porzana porzana",
"Corncrake"=>"Crex crex",
"Common Crane"=>"Grus grus",
"Avocet"=>"Recurvirostra avosetta",
