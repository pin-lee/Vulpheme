//
// Created by B "Pin" Lee on 11/30/23.
//

#ifndef ANNA_COMBINATOR_H
#define ANNA_COMBINATOR_H

template<typename IN>
void combinator(void(*fn)(IN)...) {
	fn();
}

#endif //ANNA_COMBINATOR_H
