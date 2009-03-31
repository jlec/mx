#include <stdio.h>
#include <stdlib.h>

#include <clutter/clutter.h>
#include <nbtk/nbtk.h>

int
main (int argc, char *argv[])
{
  NbtkWidget *scroll, *view, *table, *label;
  ClutterActor *stage;
  gdouble row_size;
  int i;

  clutter_init (&argc, &argv);

  nbtk_style_load_from_file (nbtk_style_get_default (),
                             "style/default.css", NULL);

  stage = clutter_stage_get_default ();
  clutter_actor_set_size (stage, 200, 200);

  scroll = (NbtkWidget *) nbtk_scroll_view_new ();
  clutter_container_add (CLUTTER_CONTAINER (stage), CLUTTER_ACTOR (scroll), NULL);
  clutter_actor_set_size (CLUTTER_ACTOR (scroll), 150, 150);

  view = (NbtkWidget *) nbtk_viewport_new ();
  clutter_container_add (CLUTTER_CONTAINER (scroll), CLUTTER_ACTOR (view), NULL);

  table = nbtk_table_new ();
  clutter_container_add (CLUTTER_CONTAINER (view), CLUTTER_ACTOR (table), NULL);

  row_size = 0;
  for (i = 0; i < 15; i++)
    {
      char *text = g_strdup_printf ("label %d", i);
      label = nbtk_label_new (text);
      nbtk_table_add_widget (NBTK_TABLE (table), label, i, 0);
      g_free (text);

      if (row_size < clutter_actor_get_height (CLUTTER_ACTOR (label)))
        row_size = clutter_actor_get_height (CLUTTER_ACTOR (label));
    }

  nbtk_scroll_view_set_row_size (NBTK_SCROLL_VIEW (scroll), row_size);
  printf ("Row size: %.2f\n", nbtk_scroll_view_get_row_size (NBTK_SCROLL_VIEW (scroll)));

  clutter_actor_show (stage);
  clutter_main ();

  return EXIT_SUCCESS;
}
