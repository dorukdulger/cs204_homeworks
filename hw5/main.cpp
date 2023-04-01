#include <iostream>
#include "SUBook.h"
using namespace std;
void printPost(Post& post){
    cout <<  "|||||||||||||||||||||||||||||||||||||||" << endl;
    cout << post.getUser().getName() <<":" << endl;
    cout << post.getContent()<< endl;
    vector<Comment*> comments = post.getComments();
    for (int i =0; i < comments.size(); i++){
        cout << "  " << comments[i]->getUser().getName();
        cout << ": " << comments[i]->getContent() << endl;
    }
    cout <<  "|||||||||||||||||||||||||||||||||||||||" << endl <<
    endl;
}
void printUserNumComments(User& user){
    cout << "User " << user.getName() << " has " <<
    user.getNumComments() << " comments" << endl << endl;
}

//int main() {
//    User u1("User1");
//       {
//           User u2("User2");
//           Post& p1 = u2.createPost("User2 post");
//           p1.addComment("User1 comment", &u1);
//           p1.addComment("User2 comment", &u2);
//           cout << u2.getName() << " has " << u2.getNumComments() << " comments" << endl;
//           cout << u1.getName() << " has " << u1.getNumComments() << " comments" << endl;
//       }
//       cout << u1.getName() << " has " << u1.getNumComments() << " comments" << endl;
//    return 0;
//}

int main() {
    User chell("Chell");
    User openai("OpenAI");
    User glados("GlaDOS");
    Post& post1= openai.createPost("Science. For humanity.");
    post1.addComment("It's the other way around.", &glados);
    post1.addComment("You monster.", &glados);
    Post& post2 = glados.createPost("Test subjects wanted. ");
    printPost(post2);
    printUserNumComments(glados);
    post2.addComment("...", &chell);
    post2.addComment("Hired.", &glados);
    printPost(post2);
    printUserNumComments(glados);
    post2.addComment("Can I be a test subject?", &openai);
    post2.addComment("Stay in your lane, Skynet.", &glados);
    printPost(post2);
    printUserNumComments(glados);
    post2.addComment("I'll bring cake.", &openai);
    post2.addComment("Welcome to the team.", &glados);
    printPost(post2);
    return 0;
}


