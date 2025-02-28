
#include "../../inc/minishell.h"

/*
// void	ft_exit(const char *msg)
// {
// 	if (msg)
// 		perror(msg);
// 	rl_clear_history();
// 	addfd(0, 0);
// 	maroc(0, FULLFREE);
// 	exit(1);
// }

// static t_gc_manager*	init_gc_manager(void)
// {
// 	t_gc_manager	*manager;

// 	manager = malloc(sizeof(t_gc_manager));
// 	if (!manager)
// 		ft_exit("Failed to initialize GC manager");
// 	manager->gc = NULL;
// 	manager->first_iter = 0;
// }

// static void addmallocedptr(void *ptr) {
//     t_gc *new;
//     static t_gc *last = NULL;

//     new = malloc(sizeof(t_gc));
//     if (!new) {
//         ft_exit("Failed to allocate memory for GC node");
//         return;
//     }

//     new->mallocedptr = ptr;
//     new->next = NULL;
//     new->prev = last;
//     if (last) {
//         last->next = new;
//     }
//     last = new;

//     if (!manager->gc) {
//         manager->gc = new;
//     }
// }

// Free memory of a specific type
// static void free_type(t_gc *gc)
//     t_gc *curr = manager->gc;

//     while (curr) {
//         if (curr->type == type) {
//             if (curr->mallocedptr) {
//                 free(curr->mallocedptr);
//             }
//             curr->mallocedptr = NULL;
//         }
//         curr = curr->next;
//     }
// }

// static void	maroc_free(t_gc_manager **manager, int free_type)
// {
// 	if (free_type == FULLFREE)
// 		full_freemaroc(manager);
// 	else
// 		release((*manager)->gc);
// }

// void	*maroc(size_t size, int flag)
// {
// 	void				*ptr;
// 	static t_gc_manager	*gc_manager = NULL;

// 	if (!gc_manager)// first run of the program
// 		gc_manager = init_gc_manager();
// 	if (flag == ALLOC)
// 	{
// 		ptr = malloc(size);
// 		if (!ptr)
// 			return (ft_exit("Malloc failed"), NULL);
// 	}
	// else if (flag == FREE || flag == FULLFREE)
	// 	return (maroc_free(&gc_manager, flag), NULL);
	// if (gc_manager->first_iter == 0)
	// {
	// 	gc_manager->gc = malloc(sizeof(t_gc));
	// 	if (!gc_manager->gc)
	// 	{
	// 		ft_exit("Failed to allocate memory for GC manager");
	// 		return (NULL);
	// 	}
	// 	gc_manager->gc->next = NULL;
	// 	gc_manager->gc->prev = NULL;
	// 	addmallocedptr(ptr);
	// 	gc_manager->first_iter = 1;
	// }
	// else
	// 	addmallocedptr(ptr);
	// return (ptr);
// }

// Free all memory tracked by the garbage collector
// void maroc_free(int type) {
//     if (gc_manager) {
//         maroc_free_all(type);
//     }
// }
*/