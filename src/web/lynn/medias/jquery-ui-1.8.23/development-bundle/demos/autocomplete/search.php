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
"Stone Curlew"=>"Burhinus oedicnemus",
"Common Ringed Plover"=>"Charadrius hiaticula",
"Kentish Plover"=>"Charadrius alexandrinus",
"Ruff"=>"Philomachus pugnax",
"Common Snipe"=>"Gallinago gallinago",
"Black-tailed Godwit"=>"Limosa limosa",
"Common Redshank"=>"Tringa totanus",
"Sandwich Tern"=>"Sterna sandvicensis",
"Common Tern"=>"Sterna hirundo",
"Arctic Tern"=>"Sterna paradisaea",
"Little Tern"=>"Sternula albifrons",
"Black Tern"=>"Chlidonias niger",
"Barn Owl"=>"Tyto alba",
"Little Owl"=>"Athene noctua",
"Short-eared Owl"=>"Asio flammeus",
"European Nightjar"=>"Caprimulgus europaeus",
"Common Kingfisher"=>"Alcedo atthis",
"Eurasian Hoopoe"=>"Upupa epops",
"Eurasian Wryneck"=>"Jynx torquilla",
"European Green Woodpecker"=>"Picus viridis",
"Crested Lark"=>"Galerida cristata",
"White-headed Duck"=>"Oxyura leucocephala",
"Pale-bellied Brent Goose"=>"Branta hrota",
"Tawny Pipit"=>"Anthus campestris",
"Whinchat"=>"Saxicola rubetra",
"European Stonechat"=>"Saxicola rubicola",
"Northern Wheatear"=>"Oenanthe oenanthe",
"Savi`s Warbler"=>"Locustella luscinioides",
"Sedge Warbler"=>"Acrocephalus schoenobaenus",
"Great Reed Warbler"=>"Acrocephalus arundinaceus",
"Bearded Reedling"=>"Panurus biarmicus",
"Red-backed Shrike"=>"Lanius collurio",
"Great Grey Shrike"=>"Lanius excubitor",
"Woodchat Shrike"=>"Lanius senator",
"Common Raven"=>"Corvus corax",
"Yellowhammer"=>"Emberiza citrinella",
"Ortolan Bunting"=>"Emberiza hortulana",
"Corn Bunting"=>"Emberiza calandra",
"Great Cormorant"=>"Phalacrocorax carbo",
"Hawfinch"=>"Coccothraustes coccothraustes",
"Common Shelduck"=>"Tadorna tadorna",
"Bluethroat"=>"Luscinia svecica",
"Grey Heron"=>"Ardea cinerea",
"Barn Swallow"=>"Hirundo rustica",
"Hooded Crow"=>"Corvus cornix",
"Dunlin"=>"Calidris alpina",
