#include <iostream>
using namespace std;

#include "Test.h"
#include "Evaluation.h"
#include "Move.h"
#include "Piece.h"
#include "PieceList.h"
#include "Position.h"
#include "SupportFunctions.h"

Test::Test() {
}

Test::~Test() {
}

void Test::TestPieceFunctions() {
  cout << endl << "TEST: Test Piece Functions" << endl << endl;
  cout << "Not yet implemented. Try TestPieceListFunctions()" << endl;
}

void Test::TestPieceListFunctions() {
cout << endl << "TEST: Test PieceList Functions" << endl << endl;
  PieceList *WhitePieces = new PieceList();
  PieceList *BlackPieces = new PieceList();
  
  cout << "Test PieceList: Creating Pieces" << endl;
  Piece *whitepawn = new Piece(6,1,3,7);
  cout << "Writing out single Piece: ";
  whitepawn->WriteOutPiece();
  cout << " Correct: Pawn on c7." << endl;
  WhitePieces->CreatePiece(whitepawn);
  WhitePieces->CreatePiece(1,1,8,1);
  WhitePieces->CreatePiece(4,1,6,6);
  cout << "Test Writing Pieces out" << endl;
  WhitePieces->WriteOutPieces();
  cout << "Should be: (order not important)" << endl;
  cout << "Bishop on f6." << endl << "Pawn on c7." << endl << "King on h1." << endl;
  Piece *blackrook = new Piece(3,-1,4,8);
  BlackPieces->CreatePiece(blackrook);
  BlackPieces->CreatePiece(2,-1,7,8);
  BlackPieces->CreatePiece(6,-1,6,7);
  BlackPieces->CreatePiece(6,-1,8,7);
  BlackPieces->WriteOutPieces();
  
  cout << "Values of White Pieces: " << WhitePieces->GetValuePieces() << " Correct Value: 4" << endl;
  cout << "Values of Black Pieces: " << BlackPieces->GetValuePieces() << " Correct Value: 16" << endl;
  cout << "Type of white Piece on Field d8? " << WhitePieces->IsAnyPieceOnField(4,8) << " Correct Value: 0" << endl;
  cout << "Type of black Piece on Field d8? " << BlackPieces->IsAnyPieceOnField(4,8) << " Correct Value: 3" << endl;
  cout << "Get the position of the king. " << (WhitePieces->GetKing())->GetFile() << " " << (WhitePieces->GetKing())->GetRank() << " Correct values: 8 1" << endl;
  cout << "Get type and color of the black piece on field f7: " << (BlackPieces->GetPieceOnField(6,7))->GetType() << " " << (BlackPieces->GetPieceOnField(6,7))->GetColor() << " Correct Values: 6 -1" << endl;
  cout << "Get Pointer to black piece on field a1: " << BlackPieces->GetPieceOnField(1,1) << " Correct value: 0" << endl;
  
  cout << "Test PieceList: Moving Pieces" << endl;
  Move *m = new Move(3,7,4,8, blackrook->GetID(), 3);
  
  WhitePieces->MovePiece(m);
  BlackPieces->DeletePiece(m);
  
  cout << "Moving the white pawn on c7 to d8, capturing the black rook there and promoting to a rook." << endl;

  cout << "Writing out white pieces after white moved." << endl;
  WhitePieces->WriteOutPieces();
  cout << "Should be: (order not important)" << endl;
  cout << "White Bishop on f6." << endl << "White Rook on d8." << endl << "White King on h1." << endl; 
  cout << "Writing out black pieces after white moved." << endl;
  BlackPieces->WriteOutPieces();
  cout << "Should be: (order not important)" << endl;
  cout << "Black Queen on g8." << endl << "Black Pawn on f7" << endl << "Black Pawn on h7" << endl;
  
  cout << endl << "Clear the white piece list" << endl;
  WhitePieces->ClearList();
  WhitePieces->WriteOutPieces();
  cout << "Should be empty" << endl;
  delete WhitePieces;
  WhitePieces = 0x0;
  BlackPieces->SetOwner(true);
  BlackPieces->ClearList();
  delete BlackPieces;
  BlackPieces = 0x0;
  
  cout << "Should delete contained pieces too. Return pointer of the created rook: " << blackrook << endl;
  
  cout << endl << "TEST of PieceList Functions finished" << endl << endl;  
}

void Test::TestPositionFunctions() {
 cout << endl << "TEST: Test Position Functions" << endl << endl;
  cout << "Test Position: Constructing the position, checking the position, Creating new pieces, moving and capturing (deleting) pieces" << endl;
  Position *pos = new Position();
  pos->CreatePiece(1,1,1,2);
  pos->CreatePiece(2,1,4,1);
  pos->CreatePiece(1,-1,5,5);
  pos->CreatePiece(3,-1,3,3);
  pos->CreatePiece(4,-1,4,4);
  pos->WriteOutPosition();
  cout << endl << "Correct would be (without ordering):" << endl;
  cout << "It is whites turn." << endl;
  cout << "White Pieces:" << endl;
  cout << "White King on a2." << endl;
  cout << "White Queen on d1." << endl;
  cout << "Black Pieces:" << endl;
  cout << "Black King on e5." << endl;
  cout << "Black Rook on c3." << endl;
  cout << "Black Bishop on d4." << endl << endl;
  cout << "ANY Mentioning of castling or en passant is wrong!" << endl;
  cout << endl << "Moving the white queen from d1 to b3" << endl;
  Move *m = new Move(4,1,2,3);
  pos->ExecuteMove(m);
  pos->WriteOutPosition();
  delete m;
  m = 0x0;
  cout << endl << "Capturing the white queen on b3 with the black rook on c3" << endl;
  m = new Move(3,3,2,3);
  pos->ExecuteMove(m);
  pos->WriteOutPosition();
  delete m;
  m = 0x0;
  cout << endl << "Capturing the black rook on b3 with the white king on a2" << endl;
  m = new Move(1,2,2,3);
  pos->ExecuteMove(m);
  pos->WriteOutPosition();
  
  delete m;
  m = 0x0;
  delete pos;
  pos = 0x0;
  
  cout << endl << "Test Position: Test castling" << endl;
  pos = new Position(0x0,0x0,1,true,true,true,true);
  cout << pos->CanColorCastle(1,true);
  pos->CreatePiece(1,1,5,1);
  pos->CreatePiece(3,1,1,1);
  pos->CreatePiece(1,-1,5,8);
  pos->CreatePiece(3,-1,8,8);
  pos->WriteOutPosition();
  cout << endl << "White castles long and black castles short" << endl;
  Move *whitelongcastling = new Move(5,1,3,1);
  Move *blackshortcastling = new Move(5,8,7,8);
  pos->ExecuteMove(whitelongcastling);
  pos->ExecuteMove(blackshortcastling);
  pos->WriteOutPosition();
  delete pos;
  pos = 0x0;
  delete whitelongcastling;
  whitelongcastling = 0x0;
  delete blackshortcastling;
  blackshortcastling = 0x0;
  cout << endl << "Test Position: Test disallowing of castling if moving the rooks" << endl;
  pos = new Position();
  pos->CreatePiece(1,1,5,1);
  pos->CreatePiece(3,1,1,1);
  pos->CreatePiece(1,-1,5,8);
  pos->CreatePiece(3,-1,8,8);
  pos->CreatePiece(3,1,8,1);
  pos->CreatePiece(3,-1,1,8);
  pos->WriteOutPosition();
  cout << endl << "Ta1-b1" << endl;
  Move *rookmove = new Move(1,1,2,1);
  pos->ExecuteMove(rookmove);
  delete rookmove;
  rookmove = 0x0;
  pos->WriteOutPosition();
  cout << endl << "Ta8-b8" << endl;
  rookmove = new Move(1,8,2,8);
  pos->ExecuteMove(rookmove);
  delete rookmove;
  rookmove = 0x0;
  pos->WriteOutPosition();
  cout << endl << "Th1-h2" << endl;
  rookmove = new Move(8,1,8,2);
  pos->ExecuteMove(rookmove);
  delete rookmove;
  rookmove = 0x0;
  pos->WriteOutPosition();
  cout << endl << "Th8xh2" << endl;
  rookmove = new Move(8,8,8,2);
  pos->ExecuteMove(rookmove);
  delete rookmove;
  rookmove = 0x0;
  pos->WriteOutPosition();
  
  cout << endl << "Test Position: End Test castling" << endl;
  delete pos;
  pos = 0x0;
  cout << endl << "Test Position: Test en passant" << endl;  
  pos = new Position();
  pos->CreatePiece(6,1,2,2);
  pos->CreatePiece(6,-1,3,4);
  pos->CreatePiece(6,1,6,4);
  pos->CreatePiece(6,-1,7,7);
  pos->WriteOutPosition();
  cout << endl << "b2-b4" << endl;
  Move *pawnmove = new Move(2,2,2,4);
  pos->ExecuteMove(pawnmove);
  delete pawnmove;
  pawnmove = 0x0;
  pos->WriteOutPosition();
  
  cout << endl << "c4xb3 e.p." << endl;
  Move *enpassant = new Move(3,4,2,3);
  pos->ExecuteMove(enpassant);
  pos->WriteOutPosition();
  delete enpassant;
  enpassant = 0x0;  
  
  cout << endl << "f4-f5" << endl;
  pawnmove = new Move(6,4,6,5);
  pos->ExecuteMove(pawnmove);
  pos->WriteOutPosition();
  delete pawnmove;
  pawnmove = 0x0;
  
  cout << endl << "g7-g5" << endl;
  pawnmove = new Move(7,7,7,5);
  pos->ExecuteMove(pawnmove);
  pos->WriteOutPosition();
  delete pawnmove;
  pawnmove = 0x0;
  
  cout << endl << "f5xg6 e.p." << endl;
  enpassant = new Move(6,5,7,6);
  pos->ExecuteMove(enpassant);
  pos->WriteOutPosition();
  delete enpassant;
  enpassant = 0x0;
  delete pos;
  pos = 0x0;
  
  cout << "Test Position: End Test en passant" << endl << endl;
  
  cout << "Test Position: Begin Test Check" << endl << endl;
  
  cout << "Creating Position with white to move." << endl;
  
  pos = new Position(0x0,0x0,-1);
  
  cout << endl << "Setting up white king on d4 and black rook on d8" << endl;
  pos->CreatePiece(1,1,4,4);
  pos->CreatePiece(3,-1,4,8);
  cout << "Test for Check: " << pos->IsChecked() << " Correct answer: 1" << endl;
 
  cout << endl << "Setting a white rook on d5" << endl;
  pos->CreatePiece(3,1,4,5);
  cout << "Test for Check: " << pos->IsChecked() << " Correct answer: 0" << endl;
  
  cout << endl << "Setting black bishop on f6" << endl;
  pos->CreatePiece(4,-1,6,6);
  cout << "Test for Check: " << pos->IsChecked() << " Correct answer: 1" << endl;

  cout << endl << "Setting a black rook on e5" << endl;
  pos->CreatePiece(3,-1,5,5);
  cout << "Test for Check: " << pos->IsChecked() << " Correct answer: 0" << endl;

  cout << endl << "Setting a black knight on b3" << endl;
  pos->CreatePiece(5,-1,2,3);
  cout << "Test for Check: " << pos->IsChecked() << " Correct answer: 1" << endl;
  
  delete pos;
  pos = 0x0;
  
  cout << endl << "Creating Position with black king on e5 and white Queen on h5" << endl;
  pos = new Position();
  pos->CreatePiece(1,-1,5,5);
  pos->CreatePiece(2,1,8,5);
  cout << "Test for Check: " << pos->IsChecked() << " Correct answer: 1" << endl;
  delete pos;
  pos = 0x0;
  
  cout << endl << "Creating Position with black king on e5 and white pawn on f4" << endl;
  pos = new Position();
  pos->CreatePiece(1,-1,5,5);
  pos->CreatePiece(6,1,6,4);
  cout << "Test for Check: " << pos->IsChecked() << " Correct answer: 1" << endl;
  delete pos;
  pos = 0x0;

  cout << endl << "Creating Position with white king on e5 and black pawn on d6" << endl;
  pos = new Position(0x0,0x0,-1);
  pos->CreatePiece(1,1,5,5);
  pos->CreatePiece(6,-1,4,6);
  cout << "Test for Check: " << pos->IsChecked() << " Correct answer: 1" << endl;
  delete pos;
  pos = 0x0;
 
  cout << endl << "Test Position: End Test Check" << endl << endl;
  
}