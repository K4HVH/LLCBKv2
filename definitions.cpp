#include "definitions.h"

// ngl, chat gpt gave me a hand with this one, shit was fucked
// and also, no one on stack overflow had a answer this easy so :/

template<typename T>
class ChainRange {
public:
    class iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        explicit iterator(const ChainRange& cr, T value) : cr(cr), value(value) {}

        T operator*() const {
            return value;
        }

        iterator& operator++() {
            value += cr.step;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return (cr.step > 0 && value < other.value) || (cr.step < 0 && value > other.value);
        }

    private:
        const ChainRange& cr;
        T value;
    };

    ChainRange(T start, T stop, T step) : start(start), stop(stop), step(step) {}

    iterator begin() const {
        return iterator(*this, start);
    }

    iterator end() const {
        return iterator(*this, stop);
    }

private:
    T start;
    T stop;
    T step;
};

std::vector<int> iter::LEDS_BOTH(int r1start, int r1stop, int r2start, int r2stop, int step = 1) {
    std::vector<int> result;

    ChainRange<int> range1(rings.large.relative.ringStartLed[r1start], rings.large.relative.ringEndLed[r1stop], step);
    ChainRange<int> range2(rings.small.relative.ringStartLed[r2start], rings.small.relative.ringEndLed[r2stop], step);

    std::copy(range1.begin(), range1.end(), std::back_inserter(result));
    std::copy(range2.begin(), range2.end(), std::back_inserter(result));

    return result;
}

std::vector<int> iter::LEDS_LARGE(int r1start, int r1stop, int step = 1) {
    std::vector<int> result;

    ChainRange<int> range1(rings.large.relative.ringStartLed[r1start], rings.large.relative.ringEndLed[r1stop], step);

    std::copy(range1.begin(), range1.end(), std::back_inserter(result));

    return result;
}

std::vector<int> iter::LEDS_SMALL(int r1start, int r1stop, int step = 1) {
    std::vector<int> result;

    ChainRange<int> range1(rings.small.relative.ringStartLed[r1start], rings.small.relative.ringEndLed[r1stop], step);

    std::copy(range1.begin(), range1.end(), std::back_inserter(result));

    return result;
}