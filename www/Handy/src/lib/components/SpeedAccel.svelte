<script>
	import MeterAlt from "carbon-icons-svelte/lib/MeterAlt.svelte";
	import { Button, ButtonSet, NumberInput } from "carbon-components-svelte";
	import { baseURL } from "$lib/store";
	let speed = 0;
	let accel = 0;
	let maxspeed = 0;
	const reset_steps = () => {
		speed = 0;
		accel = 0;
	};
	const execute = async () => {
		const url = `${baseURL}/flow/${speed}/${maxspeed}/${accel}`;
		await fetch(url, {
			method: "GET",
		});
	};
</script>

<div class="container">
	<div class="title">
		<h5>Motor Flow</h5>
		<MeterAlt size={24} style="margin-inline: 1rem;" />
	</div>
	<NumberInput
		label={"Acceleration:"}
		bind:value={accel}
		step={10}
		min={0}
		max={100}
	/>
	<NumberInput
		bind:value={maxspeed}
		label={"Max Speed:"}
		step={100}
		min={0}
		max={10000}
	/>
	<NumberInput
		bind:value={speed}
		label={"Speed:"}
		step={100}
		min={0}
		max={10000}
	/>

	<div class="button-set">
		<ButtonSet>
			<Button on:click={reset_steps} kind={"secondary"}>Reset</Button>
			<Button on:click={execute}>Execute</Button>
		</ButtonSet>
	</div>
</div>

<style scoped>
	.title {
		display: flex;
		justify-self: center;
		align-self: center;
		justify-content: center;
		align-items: center;
	}
	.container {
		display: flex;
		flex-direction: column;
		gap: 0.5rem;
		padding: 0.75rem;
	}
	.button-set {
		width: 0;
	}
</style>
