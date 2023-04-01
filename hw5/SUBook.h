#ifndef SUBook_h
#define SUBook_h

#include <string>
#include <vector>

using namespace std;

class User;
class Post;
class Comment;

class User {
    private:
        string name;
        vector<Post*> posts;
        int num_comments;
        
    public:
        User(string name);
        ~User();
        
        Post& createPost(string content);
        vector<Post*> getPosts();
        int getNumComments();
        string getName();
        friend class Comment;
};

class Post {
    public:
        Post(User& user, string content);
        ~Post();
        
        void addComment(string content, User* commenter);
        vector<Comment*> getComments();
        User& getUser();
        string getContent();
        friend class Comment;
    private:
        User& user;
        string content;
        vector<Comment*> comments;
};

class Comment {
    public:
        Comment(User& user, Post& post, string content);
        ~Comment();
        
        User& getUser();
        string getContent();
        Post& getPost();
        friend class User;
        
    private:
        User& user;
        Post& post;
        string content;
};

#endif /* Header_h */
