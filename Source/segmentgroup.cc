    return false;
}

Utilities::SegmentGroup::SegmentGroup() {
    /* Empty Constructor */
}

Utilities::SegmentGroup::~SegmentGroup() {
    while(!this->segments.empty()) {
        PathSegment* temp = this->segments.back();
        segments.pop_back();
        delete(temp);
    }
}

unsigned Utilities::SegmentGroup::size() const {
    return this->segments.size();
}

PathSegment* Utilities::SegmentGroup::at(unsigned index) const {
    return this->segments.at(index);
}

bool Utilities::SegmentGroup::empty() const {
    return this->segments.empty();
}

bool Utilities::SegmentGroup::contains(const Point& point) {
    for(unsigned i = 0; i < this->segments.size(); i++) {
        if(on_segment(segments.at(i)->get_source(),segments.at(i)->get_sink(),point)) {
            return true;
        }
    }
    return false;
}

int Utilities::SegmentGroup::get_length() {
    int total_length = 0;
    for(int i = 0; i < this->segments.size(); i++) {
        total_length += this->segments.at(i)->get_length();
    }
    return total_length;
}

void Utilities::SegmentGroup::print() {
    if(this->segments.size() <= 0) {
        cout << "Empty path" << endl;
        //return;
    }
    else{
    for(unsigned i = this->segments.size() - 1; i > 0; --i) {
        this->segments.at(i)->print();
        Point check = this->segments.at(i)->get_source();
        if((i > 0) && (check.x != -10)) {//prints in the reverse direction
            cout << " | ";
        }
    }
    //cout << " | ";
"segmentgroup.cc" 118L, 3594C                                                                                                                                                                                                      66,2-9        21%
