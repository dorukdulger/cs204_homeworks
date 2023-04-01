//#include "BitRepresentation.cpp"

//#include "BitRepresentation.h"
//#include <vector>
//using namespace std;
//int main() {
//    vector<bool> v1 = {true, false, true, false}; // == 0b1010 BitRepresentation<char> s1(v1); // s1.data = 0b00001010
//    vector<bool> v2 = {true, true, true, true, false, false, false, false}; BitRepresentation<char> s2(v2); // s2.data = 0b11110000
//    vector<bool> v3 = {true, false, false, true, true, true, true, true, true,
//        false, false, false, false};
//    BitRepresentation<char> s3(v3); // s3.data = 0b11110000
//    // since the char data type has only 8 bits, only the last 8 // booleans in v3 were used to initialize s3.data.
//    // The rest (i.e. the first 5 elements of v3) were discarded.
//    return 0;
//}


//#include "BitRepresentation.h"
//#include <iostream>
//using namespace std;
//int main() {
//    BitRepresentation<char> x(0);
//    cout << x.getBinary() << endl;
//    BitRepresentation<char> y(3);
//    cout << y.getBinary() << endl;
//    return 0;
//}

//#include "BitRepresentation.h"
//#include <iostream>
//using namespace std;
//int main() {
//    BitRepresentation<short> x(0);
//    cout << x.getHexadecimal() << endl;
//    BitRepresentation<short> y(12351);
//    cout << y.getHexadecimal() << endl;
//    return 0;
//}

//#include "BitRepresentation.h"
//#include <iostream>
//
//using namespace std;
//
//int main() {
//    BitRepresentation<char> x(0);
//    x.setBit(0);
//    cout << x.getBinary() << endl;
//    x.setBit(1);
//    cout << x.getBinary() << endl;
//    x.setBit(6);
//    cout << x.getBinary() << endl;
//    x.setBit(8); // function will do nothing in this case
//    cout << x.getBinary() << endl;
//    return 0;
//}

//#include "BitRepresentation.h"
//#include <iostream>
//using namespace std;
//int main() {
//    BitRepresentation<char> x(255);
//    cout << x.getBinary() << endl;
//    x.unsetBit(0);
//    cout << x.getBinary() << endl;
//    x.unsetBit(1);
//    cout << x.getBinary() << endl;
//    x.unsetBit(6);
//    cout << x.getBinary() << endl;
//    x.unsetBit(8); // function will do nothing in this case
//    cout << x.getBinary() << endl;
//    return 0;
//}

//#include "BitRepresentation.h"
//#include <iostream>
//using namespace std;
//int main() {
//    BitRepresentation<char> x(255);
//    x.unsetBit(0);
//    x.unsetBit(1);
//    x.unsetBit(6);
//    cout << x.getBinary() << endl;
//    cout << x.isBitSet(0) << endl;
//    cout << x.isBitSet(2) << endl;
//    cout << x.isBitSet(6) << endl;
//    cout << x.isBitSet(11) << endl;
//    return 0;
//}


//#include "BitRepresentation.h"
//#include <iostream>
//using namespace std;
//int main() {
//    BitRepresentation<short> s(0);
//    s.setBit(0);
//    s.setBit(1);
//    s.setBit(3);
//    short number = s.getNumber();
//    cout << number << endl;
//    return 0;
//}



//#include "BitRepresentation.h"
//#include <iostream>
//using namespace std;
//template <typename T>
//void get_size(){
//    cout << "Size of T " << sizeof(T) << endl;
//}
//int main() {
//    get_size<int>();
//    get_size<char>();
//    get_size<short>();
//    get_size<unsigned long>();
//    return 0;
//}



