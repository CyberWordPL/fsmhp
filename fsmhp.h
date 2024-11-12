#ifndef __FSMHP_H
#define __FSMHP_H

#include <stdint.h>
#include <stdbool.h>

typedef fsm_event_reaction_t uint8_t; 

typedef fsm_state_column_t struct _fsm_state_column_s {
	fsm_event_reaction_t *events_reactions;
};

typedef struct _fsm_s {
	uint8_t states_c;
	uint8_t events_c;
	fsm_state_column_t* states_a;
	uint8_t current_state;
} fsm_t;

bool create_fsm(fsm_t *fsm, uint8_t states, uint8_t events);
bool fsm_call_event(fsm_t *fsm, uint8_t eventId);

#ifdef FSM_IMPLEMENTATION

bool create_fsm(fsm_t *fsm, int states, int events) {
	fsm = malloc(sizeof(fsm_t));
	if (fsm == NULL) return false;
	
	fsm->states_c = states;
	fsm->events_c = events;
	fsm->current_state = 0;

	fsm->states_a = calloc(states, sizeof(fsm_state_columns_t));
	if(fsm->states_a == NULL) return false;
	
	for(int i = 0; i < fsm->states_c; i++) {
		fsm->states_a[i].events_reaction = calloc(fsm->events_c, sizeof(fsm_event_reaction_t));
		if(fsm->states_a[i].event_reaction == NULL)
			return false;
	}		
	
	return true;
}

bool fsm_call_event(fsm_t *fsm, uint8_t event_id) {
	if(eventId >= fsm->events_c) return false;
	uint8_t state = fsm->states_a[fsm->current_state].event_reactions[event_id];
	if(state >= fsm->states_c) return false;
	fsm->current_state = state;
	return true;
}

#endif

#endif
