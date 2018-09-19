open BsReactNative;

type duration = {
    duration: int,
    current: int,
    formatted: string,
    percentage: int,
}

type state = {
    timer: option(duration)
};

type action =
  | Start(int)
  | Tick
  | Cancel
  | Stop;

module Styles = {
    open Style;

    let button = style([marginTop(Pt(30.))]);
    let text = style([color(String("#fff")), fontSize(Float(22.)), marginTop(Pt(30.))]);
};

let timerId = ref(Js.Global.setTimeout(() => (), 0))

let to_percent = n => int_of_float(100. *. n);

let format_timer = (time) => {
    let minutes = time / 60;
    let seconds = time mod 60;
    let mins = minutes < 10 ? "0" ++ string_of_int(minutes) : string_of_int(minutes);
    let secs = seconds < 10 ? "0" ++ string_of_int(seconds) : string_of_int(seconds);
    mins ++ ":" ++ secs;
}

let component = ReasonReact.reducerComponent("Timer");

let make = _children => {
  ...component,
  initialState: () => {
    timer: None
  },
  reducer: (action, state) => {
    switch(action) {
    | Start(time) => {
        let duration = {
          duration: time,
          current: time + 1,
          formatted: format_timer(time),
          percentage: 0
        };

        ReasonReact.UpdateWithSideEffects({timer: Some(duration)}, self => self.send(Tick));
    }
    | Tick => {
        switch (state.timer) {
        | Some({duration, current}) => {
            let current_tick = current - 1;

            let nextDuration = {
                duration, 
                current: current_tick,
                formatted: format_timer(current_tick),
                percentage: float_of_int(duration - current_tick) /. float_of_int(duration) |> to_percent
            }

            ReasonReact.UpdateWithSideEffects({timer: Some(nextDuration)}, self => {
                current_tick === 0
                ? self.send(Stop)
                : timerId := Js.Global.setTimeout(() => self.send(Tick), 1000)
            })
        }
        | None => ReasonReact.NoUpdate
        }
    }
    | Cancel => {
        Js.Global.clearTimeout(timerId^)
        ReasonReact.Update({timer: None})
    }
    | Stop => ReasonReact.Update({timer: None})
    };
  },
  render: ({state, send}) =>
    <View>
        (
            switch (state.timer) {
            | Some(duration) =>
                <View style=Styles.button>
                    <Button title="Cancel" onPress=(_evt => send(Stop)) color="#DC143C" />
                    <Text style=Styles.text>(ReasonReact.string(duration.formatted))</Text>
                    <Text style=Styles.text>(ReasonReact.string(string_of_int(duration.percentage) ++ "%"))</Text>
                </View>
            | None =>
              <View style=Styles.button>
                <Button title="Start" onPress=(_evt => send(Start(10))) color="#DC143C" />
              </View>
            }
        )
    </View>
};
