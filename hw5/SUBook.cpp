#include "SUBook.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

User::User(string name) : name(name), num_comments(0) {}

User::~User() {
    for (int i = 0; i < posts.size(); i++) {
        delete posts[i];
    }
}

Post& User::createPost(string content) {
    Post* post = new Post(*this ,content);
    posts.push_back(post);
    return *post;
}

vector<Post*> User::getPosts() {
    return posts;
}

int User::getNumComments() {
    return num_comments;
}

string User::getName() {
    return name;
}

Post::Post(User& user, string content) : user(user), content(content) {}

Post::~Post() {
    for (Comment* comment : comments) {
        delete comment;
    }
}

void Post::addComment(string content, User* commenter) {
    Comment* comment = new Comment(*commenter, *this, content);
    comments.push_back(comment);
}

vector<Comment*> Post::getComments() {
    return comments;
}

User& Post::getUser() {
    return user;
}

string Post::getContent() {
    return content;
}

Comment::Comment(User& user, Post& post, string content) : user(user), post(post), content(content) {
    user.num_comments++;
}

Comment::~Comment() {
    user.num_comments--;
}

User& Comment::getUser() {
    return user;
}

string Comment::getContent() {
    return content;
}

Post& Comment::getPost() {
    return post;
}
