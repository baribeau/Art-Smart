// Julia Baribeau and Joanna Diao
// Note: We had some compilation errors with "auto", and we think this
//      is due to our version of the compiler. Hopefully you will not
//      have the same isue.
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <assert.h>

using namespace std;

// Purpose: Store data associated with artwork objects
class Artwork {
protected:
    string artist_name, art_title;
    unsigned int year_made;

public:
    Artwork() { // Default constructor
        artist_name = "Artist";
        year_made = 0;
        art_title = "Title";
    }

    Artwork(string name, unsigned int year, string title) :
        year_made(year), artist_name(name), art_title(title)
        {} // Parametric constructor

    // Getter functions
    string get_artist_name() {
        return artist_name;
    }
    string get_art_title() {
        return art_title;
    }
    unsigned int get_year_made() {
        return year_made;
    }

    // Equal operator overloading for Artwork objects
    bool operator==(const Artwork& target) const {
        bool are_equal = true;
        are_equal = are_equal && (artist_name == target.artist_name);
        are_equal = are_equal && (year_made == target.year_made);
        are_equal = are_equal && (art_title == target.art_title);
        return are_equal;
    }

    /*
    // Output operator overloading
    ostream& operator<<(ostream& os, const Artwork& art){
    return os ;
    }
    */

    // Give display to console function access to private members
    friend display();
};

// Purpose: Store data assocated with artwork that has been sold
class SoldArtwork : public Artwork {
    string cust_name;
    string cust_address;
    double sale_amount;

public:
    //SoldArtwork(Artwork my_artwork) : Artwork(my_artwork) {}
    SoldArtwork() : cust_name("Name"), sale_amount(0),
                    cust_address("Address"){} // Default constructor

    // Parametric constructor
    SoldArtwork(string name, string address, double amount,
                Artwork art) : cust_name(name), cust_address(address),
                sale_amount(amount), Artwork(art){}

        // Getter functions
		string get_cust_name() {
        	return cust_name;
		}
        double get_sale_amount() {
        	return sale_amount;
		}
		string get_cust_address() {
			return cust_address;
		}

    // Equal operator overloading for SoldArtwork object
	bool operator==(const SoldArtwork& target) const {
	        bool are_equal = true;
	        are_equal = are_equal && (cust_name == target.cust_name);
	        are_equal = are_equal && (cust_address == target.cust_address);
	        are_equal = are_equal && (sale_amount == target.sale_amount);
	        are_equal = are_equal && (static_cast<Artwork>(*this) == static_cast<Artwork>(target));
	        return are_equal;
	    }
};

// Purpose: Store data for art collection objects
class ArtCollection {
    vector<Artwork> my_artwork;
    vector<SoldArtwork> my_sold_artwork;

public:
    // Add an artwork object to a collection and return if successful
	bool insert_artwork(const Artwork& artwork_info){
	    for(int index=0; index < my_artwork.size(); ++index){
	        if(artwork_info == my_artwork[index])
	            return false;
	    }
	    my_artwork.push_back(artwork_info);
	    return true;
	}

    // Sell an Artwork object from the collection and return success
	bool sell_artwork(const Artwork& artwork_info, string name0,
                   string address0, double amount0){
	    bool match = false;
	    for(int index=0; index < my_artwork.size(); ++index){
	        if(artwork_info == my_artwork[index]){
                SoldArtwork my_artwork_sold =
                SoldArtwork(name0, address0, amount0, artwork_info);
                my_sold_artwork.push_back(my_artwork_sold);
	            my_artwork.erase(my_artwork.begin() + index);
	            match = true;
	        }
	    }
	    return match;
	}

    // Display the attributes of Artwork and SoldArtwork to console
	void display() {
		for(auto my_it = my_artwork.begin(); my_it !=
            my_artwork.end(); ++my_it) {
			cout<<(*my_it).get_art_title ;
			cout << (*my_it).get_artist_name;
            cout << (*my_it).get_year_made;
            cout << endl;
		}
		for(auto my_it1 = my_sold_artwork.begin(); my_it1 !=
            my_sold_artwork.end(); ++my_it1) {
			cout<<(*my_it1).get_art_title ;
			cout << (*my_it1).get_cust_name;
			cout << (*my_it1).get_cust_address;
			cout << (*my_it1).get_sale_amount;
			cout << endl;
		}
	}

    // Equals operator overloading for art collections
	bool operator==(const ArtCollection& target) const {

        // Tests if collections are equal in size
	    if(my_artwork.size() != target.my_artwork.size() ||
                    my_sold_artwork.size() !=
                    target.my_sold_artwork.size())
            return false;

        // Test if collection attributes are identical
        bool artwork_equal = std::equal(my_artwork.begin(),
                                        my_artwork.end(),
                                        target.my_artwork.begin());
        bool SoldArtwork_equal = std::equal(my_sold_artwork.begin(),
                                            my_sold_artwork.end(),
                                    target.my_sold_artwork.begin());

        return artwork_equal&&SoldArtwork_equal;
	}
	// Give art collection adding operator access to private members
    friend ArtCollection operator+(const ArtCollection& collection_1,
                                   const ArtCollection& collection_2);
};

// Adding operator overloading which combines two art collections
ArtCollection operator+(const ArtCollection& collection_1,
                        const ArtCollection& collection_2){
    ArtCollection collection_combined;
    for (vector<Artwork>::const_iterator it1 = collection_1.my_artwork.begin(); it1 !=
                    collection_1.my_artwork.end(); ++it1) {
        collection_combined.insert_artwork(*it1);
    }
    for (vector<Artwork>::const_iterator it2 = collection_2.my_artwork.begin(); it2 !=
                    collection_2.my_artwork.end(); ++it2) {
        collection_combined.insert_artwork(*it2);
    }
    return collection_combined;
}

// Testing all functions

// Testing equals operator overloading on Artwork class
bool test_artwork_op_overload(){
    Artwork a0, a1;
	Artwork a2("Leonardo Da Vinci", 1503, "Mona Lisa");
	Artwork a3("Leonardo Da Vinci", 1503, "Mona Lisa");
	Artwork a4("Vincent Van Gogh", 1889, "Starry Night");
    bool success = true;

    success = success && (a2==a3);
    success = success && (a0==a1);
    success = success && (!(a3==a4));
    return success;
}

// Testing equals operator overloading on SoldArtwork class
bool test_sold_artwork_op_overload(){
    SoldArtwork sa0, sa1;
    Artwork a0;
	Artwork a1("Leonardo Da Vinci", 1503, "Mona Lisa");
	Artwork a2("Joanna Diao", 2009, "Man Eating Potatoes");
	SoldArtwork sa2("Julia Baribeau", "123 Sesame St, USA", 2603048.05, a2);
	SoldArtwork sa3("Igor Ivkovic", "42 Grateproff Rd, Canada", 3.141592, a1);
	SoldArtwork sa4("Igor Ivkovic", "42 Grateproff Rd, Canada", 256, a0);

	bool success = true;
	success = success && (sa0==sa1);
    success = success && (!(sa2==sa4));
	success = success && (!(sa3==sa4));
    return success;
}



// Testing insert artwork function in ArtCollection class
bool test_insert_artwork(){
    Artwork a0, a1;
	Artwork a2("Leonardo Da Vinci", 1503, "Mona Lisa");
	Artwork a3("Leonardo Da Vinci", 1503, "Mona Lisa");
	Artwork a4("Vincent Van Gogh", 1889, "Starry Night");
	Artwork a5("Joanna Diao", 2009, "Man Eating Potatoes");

	bool success = true;
    ArtCollection ac0;
    success = success && (ac0.insert_artwork(a0));
    success = success && (!(ac0.insert_artwork(a0)));
    success = success && (!(ac0.insert_artwork(a1)));
    success = success && (ac0.insert_artwork(a2));

	return success;
}

// Testing sell artwork function in ArtCollection class
bool test_sell_artwork() {
	ArtCollection ac0;
    Artwork a0("Leonardo Da Vinci", 1503, "Mona Lisa");
    Artwork a1("Leonardo Da Vinci", 1503, "Mona Lisa");
	ac0.insert_artwork(a0);
	//Test if sell_artwork can successfully delete the artwork
	assert(ac0.sell_artwork(a0, "Julia Baribeau", "123 Sesame St", 20.50));
	//Test if sell_artwork can recognize that a0 was already sold
	assert(!ac0.sell_artwork(a0, "Joanna Diao", "122 Sesame St", 20));
	//Test if sell_artwork can recognize that a1 does not exist in ac0
	assert(!ac0.sell_artwork(a1, "Joanna Diao", "122 Sesame St", 20));
    return true;
}

// Testing addition operator on art collection classes
bool test_art_collection_op_overload(){
    Artwork a0, a1;
	Artwork a2("Leonardo Da Vinci", 1503, "Mona Lisa");
	Artwork a3("Leonardo Da Vinci", 1503, "Mona Lisa");
	Artwork a4("Vincent Van Gogh", 1889, "Starry Night");
	Artwork a5("Joanna Diao", 2009, "Man Eating Potatoes");

    ArtCollection ac0, ac1, ac2, ac3, ac4;
	ac0.insert_artwork(a0);
	ac0.insert_artwork(a1);
	ac0.insert_artwork(a2);

	ac1.insert_artwork(a3);
	ac1.insert_artwork(a4);
	ac1.insert_artwork(a5);

	ac2.insert_artwork(a0);
	ac2.insert_artwork(a4);
	ac2.insert_artwork(a5);

	ac3 = ac1+ac0;
	ac4 = ac1+ac2;

    ac3.display();
    ac4.display();
}

int main(){
	cout<< "Artwork operator overloading: " << test_artwork_op_overload() << endl;
	cout<< "SoldArtwork operator overloading: " << test_sold_artwork_op_overload() << endl;
	cout<< "Insert artwork function: " << test_insert_artwork() << endl;
	cout<< "SoldArtwork operator overloading: " << test_sell_artwork() << endl;
	cout << "SoldArtwork operator overloading: " << test_art_collection_op_overload()<< endl;
	system("PAUSE");
	return 1;
}



