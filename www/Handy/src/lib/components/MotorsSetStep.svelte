<script>
	import ChartAreaStepper from "carbon-icons-svelte/lib/ChartAreaStepper.svelte";
	import { Button, ButtonSet, NumberInput } from "carbon-components-svelte";
	import { baseURL } from "$lib/store";

	let motor_1_step = 0;
	let motor_2_step = 0;
	let motor_3_step = 0;

	const reset_steps = () => {
		motor_1_step = 0;
		motor_2_step = 0;
		motor_3_step = 0;
	};
	const execute = async () => {
		const url = `${baseURL}/steps/${motor_1_step}/${motor_2_step}/${motor_3_step}`;
		await fetch(url, {
			method: "GET",
		});
	};
</script>

<div class="container">
	<div class="title">
		<h5>Motor Steps</h5>
		<ChartAreaStepper size={24} style={"margin-inline:1rem"} />
	</div>

	<NumberInput label={"Motor 1:"} bind:value={motor_1_step} step={100} />
	<NumberInput bind:value={motor_2_step} label={"Motor 2:"} step={100} />
	<NumberInput bind:value={motor_3_step} label={"Motor 3:"} step={100} />
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
